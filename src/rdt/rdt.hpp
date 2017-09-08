// Copyright (c) 2017 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SNAP_PLUGIN_COLLECTOR_RDT_RDT_HPP
#define SNAP_PLUGIN_COLLECTOR_RDT_RDT_HPP

#include <vector>

#include "pqos.hpp"

#include "snap/plugin.h"
#include "snap/config.h"
#include "snap/metric.h"


namespace rdt
{
    extern Plugin::Namespace cmt_capability_ns;
    extern Plugin::Namespace mbm_local_monitoring_ns;
    extern Plugin::Namespace mbm_remote_monitoring_ns;
    extern Plugin::Namespace l3ca_ns;
    extern Plugin::Namespace llc_size_ns;
    extern Plugin::Namespace cache_ways_count_ns;
    extern Plugin::Namespace cache_way_size_ns;

    class Collector : public Plugin::CollectorInterface
    {
    public:
        Collector(PQOSInterface *pqos);
        ~Collector();

        const Plugin::ConfigPolicy get_config_policy();
        std::vector<Plugin::Metric> get_metric_types(Plugin::Config cfg);
        std::vector<Plugin::Metric> collect_metrics(std::vector<Plugin::Metric> &metrics);
        Plugin::Meta get_plugin_meta();

        std::string name = "rdt";
        int version = 1;

    private:
        Collector(const Collector &that){};

        std::vector<Plugin::Metric> get_cmt_metrics();

        void setup_monitoring();
        void poll_metrics();

        std::vector<Plugin::Metric> get_capabilities_metrics();
        std::vector<Plugin::Metric> get_mbm_metrics();

        bool is_monitoring_active;
        std::vector<pqos_mon_data *> groups;

        bool cmt_capability;
        bool mbm_local_capability;
        bool mbm_remote_capability;
        bool l3ca_capability; // L3 Cache Allocation Capability.

        int core_count;
        int llc_size;
        int cache_ways_count;
        int cache_way_size;

        PQOSInterface *pqos;
    };

}  // namespace rdt

#endif //SNAP_PLUGIN_COLLECTOR_RDT_RDT_HPP
