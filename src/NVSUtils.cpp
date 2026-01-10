#include "NVSUtils.h"
#include <Arduino.h>
#include <nvs.h>
#include <nvs_flash.h>

void NVSUtils::copyNamespace(const char *src_ns, const char *dst_ns) {
  nvs_handle_t h_src, h_dst;
  esp_err_t err;

  // Try to open source namespace
  err = nvs_open(src_ns, NVS_READONLY, &h_src);
  if (err != ESP_OK) {
    if (err == ESP_ERR_NVS_NOT_FOUND) {
      // Source doesn't exist/empty. Just ensure destination is cleared
      err = nvs_open(dst_ns, NVS_READWRITE, &h_dst);
      if (err == ESP_OK) {
        nvs_erase_all(h_dst);
        nvs_commit(h_dst);
        nvs_close(h_dst);
      }
    }
    return;
  }

  // Open destination namespace
  err = nvs_open(dst_ns, NVS_READWRITE, &h_dst);
  if (err != ESP_OK) {
    nvs_close(h_src);
    return;
  }

  // Clear destination first to ensure exact copy
  nvs_erase_all(h_dst);

  // Iterate over all entries in source namespace
  nvs_iterator_t it = nvs_entry_find("nvs", src_ns, NVS_TYPE_ANY);
  while (it != NULL) {
    nvs_entry_info_t info;
    nvs_entry_info(it, &info);

    // Copy based on type
    switch (info.type) {
    case NVS_TYPE_U8: {
      uint8_t v;
      nvs_get_u8(h_src, info.key, &v);
      nvs_set_u8(h_dst, info.key, v);
      break;
    }
    case NVS_TYPE_I8: {
      int8_t v;
      nvs_get_i8(h_src, info.key, &v);
      nvs_set_i8(h_dst, info.key, v);
      break;
    }
    case NVS_TYPE_U16: {
      uint16_t v;
      nvs_get_u16(h_src, info.key, &v);
      nvs_set_u16(h_dst, info.key, v);
      break;
    }
    case NVS_TYPE_I16: {
      int16_t v;
      nvs_get_i16(h_src, info.key, &v);
      nvs_set_i16(h_dst, info.key, v);
      break;
    }
    case NVS_TYPE_U32: {
      uint32_t v;
      nvs_get_u32(h_src, info.key, &v);
      nvs_set_u32(h_dst, info.key, v);
      break;
    }
    case NVS_TYPE_I32: {
      int32_t v;
      nvs_get_i32(h_src, info.key, &v);
      nvs_set_i32(h_dst, info.key, v);
      break;
    }
    case NVS_TYPE_U64: {
      uint64_t v;
      nvs_get_u64(h_src, info.key, &v);
      nvs_set_u64(h_dst, info.key, v);
      break;
    }
    case NVS_TYPE_I64: {
      int64_t v;
      nvs_get_i64(h_src, info.key, &v);
      nvs_set_i64(h_dst, info.key, v);
      break;
    }
    case NVS_TYPE_STR: {
      size_t len;
      if (nvs_get_str(h_src, info.key, NULL, &len) == ESP_OK) {
        char *v = (char *)malloc(len);
        if (v) {
          nvs_get_str(h_src, info.key, v, &len);
          nvs_set_str(h_dst, info.key, v);
          free(v);
        }
      }
      break;
    }
    case NVS_TYPE_BLOB: {
      size_t len;
      if (nvs_get_blob(h_src, info.key, NULL, &len) == ESP_OK) {
        void *v = malloc(len);
        if (v) {
          nvs_get_blob(h_src, info.key, v, &len);
          nvs_set_blob(h_dst, info.key, v, len);
          free(v);
        }
      }
      break;
    }
    }
  it = nvs_entry_next(it);
  }
  nvs_release_iterator(it);

  nvs_commit(h_dst);
  nvs_close(h_src);
  nvs_close(h_dst);
}

void NVSUtils::loadSlotBonds(uint8_t slot) {
  char slot_ns[16];
  snprintf(slot_ns, sizeof(slot_ns), "ble_bond_%d", slot);
  Serial.printf("[System] Loading BLE bonds for slot %d from '%s'...\n",
                slot + 1, slot_ns);
  copyNamespace(slot_ns, "nimble_bond");
}

void NVSUtils::saveSlotBonds(uint8_t slot) {
  char slot_ns[16];
  snprintf(slot_ns, sizeof(slot_ns), "ble_bond_%d", slot);
  Serial.printf("[System] Saving BLE bonds for slot %d to '%s'...\n", slot + 1,
                slot_ns);
  copyNamespace("nimble_bond", slot_ns);
}
