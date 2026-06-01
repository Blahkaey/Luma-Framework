#define MONSTER_HUNTER_WORLD 1

#define ENABLE_NGX 1

#include "..\..\Core\core.hpp"

// TODO: Fix this globaly? Define NOMINMAX before including windows.h.
#undef min
#undef max

struct alignas(16) CBViewProjection
{
    row_major float4x4 fViewProj;
    row_major float4x4 fView;
    row_major float4x4 fProj;
    row_major float4x4 fViewI;
    row_major float4x4 fProjI;
    row_major float4x4 fViewProjI;
    float3 fCameraPos;
    float padding1; // Added.
    float3 fCameraDir;
    float padding2; // Added.
    float3 fZToLinear;
    float fCameraNearClip;
    float fCameraFarClip;
    float fCameraTargetDist;
    float2 padding3; // Added.
    float4 fPassThrough;
    float3 fLODBasePos;
    float padding4; // Added.
    row_major float4x4 fViewProjPF;
    row_major float4x4 fViewProjIPF;
    row_major float4x4 fViewPF;
    row_major float4x4 fProjPF;
    row_major float4x4 fViewProjIViewProjPF;
    row_major float4x4 fNoJitterProj;
    row_major float4x4 fNoJitterViewProj;
    row_major float4x4 fNoJitterViewProjI;
    row_major float4x4 fNoJitterViewProjIViewProjPF;
    float2 fPassThroughCorrect;
    /*bool*/ uint bWideMonitor;
    float padding5;
};

namespace
{
    const ShaderHashesList shader_hashes_TAA = { .compute_shaders = { 0xD84C4AF0 }};
    const ShaderHashesList shader_hashes_Copy = { .pixel_shaders = { 0xBCA17DC2 }};

    float g_jitter_x;
    float g_jitter_y;

    // The game is throwing EXCEPTION_BREAKPOINT which will crash the game if debugger isn't attached (even in release build!).
    LONG CALLBACK ExceptionBreakpointHandler(EXCEPTION_POINTERS* ep)
    {
        if (ep->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT) {
            ep->ContextRecord->Rip += 1;
            return EXCEPTION_CONTINUE_EXECUTION;
        }
        return EXCEPTION_CONTINUE_SEARCH;
    }
}

struct GameDeviceDataMonsterHunterWorld final : GameDeviceData
{
};

class MonsterHunterWorld final : public Game
{
public:

    static GameDeviceDataMonsterHunterWorld& GetGameDeviceData(DeviceData& device_data)
    {
        return *(GameDeviceDataMonsterHunterWorld*)device_data.game;
    }

    void OnLoad(std::filesystem::path& file_path, bool failed = false) override
    {
        // We must remove it later with `RemoveVectoredExceptionHandler`?
        AddVectoredExceptionHandler(1, ExceptionBreakpointHandler);

        reshade::register_event<reshade::addon_event::update_buffer_region>(OnUpdateBufferRegion);
    }

    void OnInit(bool async) override
    {
       // ### Update these (find the right values) ###
       // ### See the "GameCBuffers.hlsl" in the shader directory to expand settings ###
       luma_settings_cbuffer_index = 13;
       luma_data_cbuffer_index = -1;

       native_shaders_definitions.emplace("MHW Unpack MVs CS"_h, ShaderDefinition{ "Luma_MHW_UnpackMVs_CS", reshade::api::pipeline_subobject_type::compute_shader });
    }

    void OnCreateDevice(ID3D11Device* native_device, DeviceData& device_data) override
    {
        device_data.game = new GameDeviceDataMonsterHunterWorld;
    }

    void OnInitSwapchain(reshade::api::swapchain* swapchain) override
    {
        auto& device_data = *swapchain->get_device()->get_private_data<DeviceData>();
        auto& game_device_data = GetGameDeviceData(device_data);
        auto& managed_resources = game_device_data.managed_resources;

        managed_resources.unordered_access_views["mvs"_h].reset();
    }

    static bool OnUpdateBufferRegion(reshade::api::device* device, const void* data, reshade::api::resource resource, uint64_t offset, uint64_t size)
    {
        auto native_resource = (ID3D11Resource*)resource.handle;
        ComPtr<ID3D11Buffer> buffer;
        auto hr = native_resource->QueryInterface(buffer.put());
        if (SUCCEEDED(hr))
        {
            D3D11_BUFFER_DESC desc;
            buffer->GetDesc(&desc);

            // This alone should be reliable? Needs testing!
            if (desc.BindFlags == D3D11_BIND_CONSTANT_BUFFER && desc.ByteWidth == 1072)
            {
                g_jitter_x = ((CBViewProjection*)data)->fProj.m20;
                g_jitter_y = ((CBViewProjection*)data)->fProj.m21;
            }
        }
        return false;
    }

    DrawOrDispatchOverrideType OnDrawOrDispatch(ID3D11Device* native_device, ID3D11DeviceContext* native_device_context, CommandListData& cmd_list_data, DeviceData& device_data, reshade::api::shader_stage stages, const ShaderHashesList<OneShaderPerPipeline>& original_shader_hashes, bool is_custom_pass, bool& updated_cbuffers, std::function<void()>* original_draw_dispatch_func) override
    {
        auto& game_device_data = GetGameDeviceData(device_data);

        if (original_shader_hashes.Contains(shader_hashes_Copy))
        {
            auto& managed_resources = game_device_data.managed_resources;

            // The shader is used to copy various resources.
            // Expecting depth to be the last before the TAA should be reliable? Needs testing!
            ComPtr<ID3D11ShaderResourceView> srv;
            native_device_context->PSGetShaderResources(0, 1, srv.put());
            if (srv) {
                srv->GetResource(managed_resources.resources["depth"_h].put());
            }

            return DrawOrDispatchOverrideType::None;
        }

        if (original_shader_hashes.Contains(shader_hashes_TAA))
        {
            if (device_data.sr_type != SR::Type::None)
            {
                // DLSS requires an immediate context for execution!
                ASSERT_ONCE(native_device_context->GetType() == D3D11_DEVICE_CONTEXT_IMMEDIATE);

                auto& managed_resources = game_device_data.managed_resources;

                // Get UAV and it's resource.
                ComPtr<ID3D11UnorderedAccessView> uav_output;
                native_device_context->CSGetUnorderedAccessViews(0, 1, uav_output.put());
                ComPtr<ID3D11Resource> resource_output;
                uav_output->GetResource(resource_output.put());

                // UnpackMVs pass
                //

                // Create UAV.
                [[unlikely]] if (!managed_resources.unordered_access_views["mvs"_h]) {
                    D3D11_TEXTURE2D_DESC tex_desc = {};
                    tex_desc.Width = device_data.render_resolution.x;
                    tex_desc.Height = device_data.render_resolution.y;
                    tex_desc.MipLevels = 1;
                    tex_desc.ArraySize = 1;
                    tex_desc.Format = DXGI_FORMAT_R16G16_FLOAT;
                    tex_desc.SampleDesc.Count = 1;
                    tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
                    ensure(native_device->CreateTexture2D(&tex_desc, nullptr, managed_resources.textures_2d["mvs"_h].put()), >= 0);
                    ensure(native_device->CreateUnorderedAccessView(managed_resources.textures_2d["mvs"_h].get(), nullptr, managed_resources.unordered_access_views["mvs"_h].put()), >= 0);
                }

                // Bindings.
                native_device_context->CSSetUnorderedAccessViews(0, 1, &managed_resources.unordered_access_views["mvs"_h], nullptr);
                native_device_context->CSSetShader(device_data.native_compute_shaders.at("MHW Unpack MVs CS"_h).get(), nullptr, 0);

                native_device_context->Dispatch((device_data.render_resolution.x + 8 - 1) / 8, (device_data.render_resolution.y + 8 - 1) / 8, 1);

                //

                // DLSS pass
                //

                auto* sr_instance_data = device_data.GetSRInstanceData();
                ASSERT_ONCE(sr_instance_data);

                SR::SettingsData settings_data;
                settings_data.output_width = device_data.output_resolution.x;
                settings_data.output_height = device_data.output_resolution.y;
                settings_data.render_width = device_data.render_resolution.x;
                settings_data.render_height = device_data.render_resolution.y;
                settings_data.dynamic_resolution = false;
                settings_data.hdr = true;
                settings_data.inverted_depth = true;
                settings_data.mvs_jittered = false;

                // MVs are in NDC space so we need to scale them to screen space for DLSS.
                settings_data.mvs_x_scale = device_data.render_resolution.x * -0.5;
                settings_data.mvs_y_scale = device_data.render_resolution.y * 0.5;

                settings_data.render_preset = dlss_render_preset;
                settings_data.auto_exposure = true;

                sr_implementations[device_data.sr_type]->UpdateSettings(sr_instance_data, native_device_context, settings_data);

                ComPtr<ID3D11ShaderResourceView> srv_scene;
                native_device_context->CSGetShaderResources(0, 1, srv_scene.put());
                ComPtr<ID3D11Resource> resorce_scene;
                srv_scene->GetResource(resorce_scene.put());

                SR::SuperResolutionImpl::DrawData draw_data;
                draw_data.source_color = resorce_scene.get();
                draw_data.output_color = resource_output.get();
                draw_data.motion_vectors = managed_resources.textures_2d["mvs"_h].get();
                draw_data.depth_buffer = managed_resources.resources["depth"_h].get();

                // Jitters are in UV offsets so we need to scale them to pixel offsets for DLSS.
                draw_data.jitter_x = g_jitter_x * device_data.render_resolution.x * -1.0f;
                draw_data.jitter_y = g_jitter_y * device_data.render_resolution.y * 1.0f;

                draw_data.render_width = device_data.render_resolution.x;
                draw_data.render_height = device_data.render_resolution.y;

                sr_implementations[device_data.sr_type]->Draw(sr_instance_data, native_device_context, draw_data);

                //

                return DrawOrDispatchOverrideType::Replaced;
            }

            return DrawOrDispatchOverrideType::None;
        }

        return DrawOrDispatchOverrideType::None;
    }

    void OnPresent(ID3D11Device* native_device, DeviceData& device_data) override
    {
        auto& game_device_data = GetGameDeviceData(device_data);

        if (!custom_texture_mip_lod_bias_offset)
        {
            std::shared_lock shared_lock_samplers(s_mutex_samplers);
            if (device_data.sr_type != SR::Type::None && !device_data.sr_suppressed)
            {
               device_data.texture_mip_lod_bias_offset = SR::GetMipLODBias(device_data.render_resolution.y, device_data.output_resolution.y); // This results in -1 at output res
            }
            else
            {
               device_data.texture_mip_lod_bias_offset = 0.0f;
            }
        }
    }

    void PrintImGuiAbout() override
    {
        ImGui::Text("Monster Hunter World Luma mod - about and credits section", "");
    }
};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        Globals::SetGlobals(PROJECT_NAME, "Monster Hunter World Luma mod");
        Globals::VERSION = 1;

        swapchain_format_upgrade_type  = TextureFormatUpgradesType::AllowedEnabled;
        swapchain_upgrade_type         = SwapchainUpgradeType::scRGB;
        texture_format_upgrades_type   = TextureFormatUpgradesType::AllowedEnabled;
        // ### Check which of these are needed and remove the rest ###
        texture_upgrade_formats = {
              //reshade::api::format::r8g8b8a8_unorm,
              //reshade::api::format::r8g8b8a8_unorm_srgb,
              //reshade::api::format::r8g8b8a8_typeless,
              //reshade::api::format::r8g8b8x8_unorm,
              //reshade::api::format::r8g8b8x8_unorm_srgb,
              //reshade::api::format::b8g8r8a8_unorm,
              //reshade::api::format::b8g8r8a8_unorm_srgb,
              //reshade::api::format::b8g8r8a8_typeless,
              //reshade::api::format::b8g8r8x8_unorm,
              //reshade::api::format::b8g8r8x8_unorm_srgb,
              //reshade::api::format::b8g8r8x8_typeless,

              reshade::api::format::r11g11b10_float,
        };
        // ### Check these if textures are not upgraded ###
        texture_format_upgrades_2d_size_filters = 0 | (uint32_t)TextureFormatUpgrades2DSizeFilters::SwapchainResolution | (uint32_t)TextureFormatUpgrades2DSizeFilters::SwapchainAspectRatio;

        enable_samplers_upgrade = true;
        
        // TODO: Remove this later!
        Globals::DEVELOPMENT_STATE = Globals::ModDevelopmentState::WorkInProgress;

        #if DEVELOPMENT
        forced_shader_names.emplace(0xD84C4AF0, "TAA");
        forced_shader_names.emplace(0xBCA17DC2, "Copy");
        #endif

        game = new MonsterHunterWorld();
    }

    CoreMain(hModule, ul_reason_for_call, lpReserved);

    return TRUE;
}