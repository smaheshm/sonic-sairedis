#include "sai_redis.h"

using namespace sairedis;

std::shared_ptr<Sai> redis_sai = std::make_shared<Sai>();

sai_status_t sai_api_initialize(
        _In_ uint64_t flags,
        _In_ const sai_service_method_table_t* service_method_table)
{
    SWSS_LOG_ENTER();

    return redis_sai->initialize(flags, service_method_table);
}

sai_status_t sai_api_uninitialize(void)
{
    SWSS_LOG_ENTER();

    return redis_sai->uninitialize();
}

sai_status_t sai_log_set(
        _In_ sai_api_t sai_api_id,
        _In_ sai_log_level_t log_level)
{
    SWSS_LOG_ENTER();

    return SAI_STATUS_NOT_IMPLEMENTED;
}

#define API(api) .api ## _api = const_cast<sai_ ## api ## _api_t*>(&redis_ ## api ## _api)

static sai_apis_t redis_apis = {
    API(switch),
    API(port),
    API(fdb),
    API(vlan),
    API(virtual_router),
    API(route),
    API(next_hop),
    API(next_hop_group),
    API(router_interface),
    API(neighbor),
    API(acl),
    API(hostif),
    API(mirror),
    API(samplepacket),
    API(stp),
    API(lag),
    API(policer),
    API(wred),
    API(qos_map),
    API(queue),
    API(scheduler),
    API(scheduler_group),
    API(buffer),
    API(hash),
    API(udf),
    API(tunnel),
    API(l2mc),
    API(ipmc),
    API(rpf_group),
    API(l2mc_group),
    API(ipmc_group),
    API(mcast_fdb),
    API(bridge),
    API(tam),
    API(segmentroute),
    API(mpls),
    API(dtel),
    API(bfd),
    API(isolation_group),
    API(nat),
    API(counter),
    API(debug_counter),
    API(macsec),
    API(bmtor),
};

static_assert((sizeof(sai_apis_t)/sizeof(void*)) == (SAI_API_EXTENSIONS_MAX - 1));

sai_status_t sai_api_query(
        _In_ sai_api_t sai_api_id,
        _Out_ void** api_method_table)
{
    SWSS_LOG_ENTER();

    if (api_method_table == NULL)
    {
        SWSS_LOG_ERROR("NULL method table passed to SAI API initialize");

        return SAI_STATUS_INVALID_PARAMETER;
    }

    if (sai_metadata_get_enum_value_name(&sai_metadata_enum_sai_api_t, sai_api_id))
    {
        *api_method_table = ((void**)&redis_apis)[sai_api_id - 1];
        return SAI_STATUS_SUCCESS;
    }

    SWSS_LOG_ERROR("Invalid API type %d", sai_api_id);

    return SAI_STATUS_INVALID_PARAMETER;
}

sai_status_t sai_query_attribute_enum_values_capability(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _In_ sai_attr_id_t attr_id,
        _Inout_ sai_s32_list_t *enum_values_capability)
{
    SWSS_LOG_ENTER();

    return redis_sai->queryAattributeEnumValuesCapability(
            switch_id,
            object_type,
            attr_id,
            enum_values_capability);
}

sai_status_t sai_object_type_get_availability(
        _In_ sai_object_id_t switch_id,
        _In_ sai_object_type_t object_type,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list,
        _Out_ uint64_t *count)
{
    SWSS_LOG_ENTER();

    return redis_sai->objectTypeGetAvailability(
            switch_id,
            object_type,
            attr_count,
            attr_list,
            count);
}

sai_object_type_t sai_object_type_query(
        _In_ sai_object_id_t objectId)
{
    SWSS_LOG_ENTER();

    return redis_sai->objectTypeQuery(objectId);
}

sai_object_id_t sai_switch_id_query(
        _In_ sai_object_id_t objectId)
{
    SWSS_LOG_ENTER();

    return redis_sai->switchIdQuery(objectId);
}
