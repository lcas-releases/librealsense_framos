// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2018 Intel Corporation. All Rights Reserved

#pragma once

#include "../include/realsense_node_factory.h"

namespace realsense2_camera
{
    class FramosRealSenseNodeFactory : public nodelet::Nodelet
    {
    public:
        FramosRealSenseNodeFactory();
        virtual ~FramosRealSenseNodeFactory();

    private:
        typedef struct camera_device
        {
            std::string serial;
            std::string usb_port_id;
            std::string ip_address;
            std::string device_type;
            std::string camera_name;
            std::string rosbag_filename;
            rs2::device device;
            bool is_found = false;
            bool is_started = false;
            bool initial_reset = false;
            std::unique_ptr<InterfaceRealSenseNode> realSenseNode;
        } camera_device;

        void closeDevice();
        void StartDevice(camera_device *device);
        void loadParameters();
        void change_device_callback(rs2::event_information& info);
        void getDevice(rs2::device_list list);
        void getDeviceFromBag();
        virtual void onInit() override;
        void tryGetLogSeverity(rs2_log_severity& severity) const;

        rs2::context _ctx;
        std::thread _query_thread;

        std::vector<camera_device*> _device_list;

    };
}//end namespace
