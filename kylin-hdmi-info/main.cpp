#include <iostream>
#include <iomanip>
#include <asm/types.h>
#include <genericLinux/include/hdmi_wrapper.h>
#include <genericLinux/include/vout_wrapper.h>
//#include <hardware/libhardware/include/hardware/hardware.h>
#include <device/realtek/proprietary/libs/HDMIControl/HDMIAdapter/HDMIAdapter_Phoenix.h>

using namespace std;

void DumpBuffer(unsigned char * buffer, size_t size)
{
    static const size_t NumColumns = 16;
    size_t offset = 0;
    while (offset < size)
    {
        for (size_t column = 0; column < NumColumns; ++column)
        {
            if (offset + column < size)
                cout << hex << setfill('0') << setw(2) << (int)buffer[offset + column];
            else
                cout << "  ";
            cout << " ";
        }
        for (size_t column = 0; column < NumColumns; ++column)
        {
            if (offset + column < size)
            {
                if (isprint(buffer[offset + column]))
                    cout << (char)buffer[offset + column];
                else
                    cout << ".";
            }
            else
                cout << " ";
            cout << " ";
        }
        cout << endl;
        offset += NumColumns;
    }
}

int main()
{
    int result;

    PhoenixHDMIAdapter adapter;

//    const hw_module_t * module;
//    result = hw_get_module("hdmi", &module);
//
//    cout << "hw_get_module(hdmi): " << result << "->" << module << endl;

//    result = hdmi_wrap_init();
//
//    cout << "hdmi_wrap_init(): " << result << endl;
//
//    unsigned char EDIDBuffer[256];
//    result = hdmi_wrap_get_EDID(EDIDBuffer);
//
//    cout << "hdmi_wrap_get_EDID(EDIDBuffer): " << result << endl;
//    if (result == 0)
//    {
//        DumpBuffer(EDIDBuffer, sizeof(EDIDBuffer));
//    }


//    result = vo_wrap_init(VO_WRAP_VIDEO_PLANE_V1);
//
//    cout << "vo_wrap_init(VO_WRAP_VIDEO_PLANE_V1): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_V1);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_V1): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_V2);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_V2): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_SUB1);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_SUB1): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_OSD1);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_OSD1): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_OSD2);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_OSD2): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN1);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN1): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN2);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN2): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN3);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN3): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN4);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN4): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN5);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN5): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN6);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN6): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN7);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN7): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN8);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_WIN8): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_SUB2);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_SUB2): " << result << endl;
//
//    result = vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_CSR);
//
//    cout << "vo_wrap_is_plane_using(VO_WRAP_VIDEO_PLANE_CSR): " << result << endl;
//
//    VOUT_BUFFER buffer;
//    buffer.width = 640;
//    buffer.height = 480;
//    buffer.stride = 2560;
//    buffer.slice_height = 0;
//
//    result =  vo_wrap_alloc_nv12_buffer(VO_WRAP_VIDEO_PLANE_V1, &buffer);
//    cout << "vo_wrap_alloc_nv12_buffer(VO_WRAP_VIDEO_PLANE_V1, &buffer): " << result << endl;
//
//    vo_wrap_v1_force_on();
//    cout << "vo_wrap_v1_force_on()" << endl;
//
//    vo_wrap_v1_set_display_window(0, 0, 640, 480);
//    cout << "vo_wrap_v1_set_display_window(0, 0, 640, 480)" << endl;
//
//    vo_wrap_v1_stop(VO_WRAP_VIDEO_PLANE_V1);
//    cout << "vo_wrap_v1_stop(VO_WRAP_VIDEO_PLANE_V1)" << endl;
//
//    result = vo_wrap_free_nv12_buffer(VO_WRAP_VIDEO_PLANE_V1, &buffer);
//    cout << "vo_wrap_free_nv12_buffer(VO_WRAP_VIDEO_PLANE_V1, &buffer): " << result << endl;
//
//    vo_wrap_deinit(VO_WRAP_VIDEO_PLANE_V1);
//    cout << "vo_wrap_deinit(VO_WRAP_VIDEO_PLANE_V1)" << endl;
//
//    hdmi_wrap_turn_off();
//
//    cout << "hdmi_wrap_turn_off()" << endl;
//
//    hdmi_wrap_deinit();
//
//    cout << "hdmi_wrap_deinit()" << endl;

    return 0;
}