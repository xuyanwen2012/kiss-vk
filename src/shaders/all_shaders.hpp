#pragma once

#include <string>
#include <unordered_map>

namespace vulkan {

namespace shaders {

#include "h/cifar_conv2d_spv.h"
#include "h/cifar_linear_spv.h"
#include "h/cifar_maxpool2d_spv.h"
#include "h/cifar_sparse_conv2d_spv.h"
#include "h/cifar_sparse_linear_spv.h"
#include "h/cifar_sparse_maxpool_spv.h"
#include "h/hello_vector_add_spv.h"
#include "h/tmp_add_base_spv.h"
#include "h/tmp_add_base_v2_16_spv.h"
#include "h/tmp_add_base_v2_32_spv.h"
#include "h/tmp_add_base_v2_64_spv.h"
#include "h/tmp_global_exclusive_scan_spv.h"
#include "h/tmp_global_exclusive_scan_v2_16_spv.h"
#include "h/tmp_global_exclusive_scan_v2_32_spv.h"
#include "h/tmp_global_exclusive_scan_v2_64_spv.h"
#include "h/tmp_local_inclusive_scan_spv.h"
#include "h/tmp_local_inclusive_scan_v2_16_spv.h"
#include "h/tmp_local_inclusive_scan_v2_32_spv.h"
#include "h/tmp_local_inclusive_scan_v2_64_spv.h"
#include "h/tmp_single_radixsort_warp16_spv.h"
#include "h/tmp_single_radixsort_warp32_spv.h"
#include "h/tmp_single_radixsort_warp64_spv.h"
#include "h/tree_build_octree_spv.h"
#include "h/tree_build_radix_tree_spv.h"
#include "h/tree_edge_count_spv.h"
#include "h/tree_find_dups_spv.h"
#include "h/tree_merge_sort_spv.h"
#include "h/tree_morton_spv.h"
#include "h/tree_move_dups_spv.h"
#include "h/tree_naive_prefix_sum_spv.h"

static std::unordered_map<std::string, std::pair<const unsigned char*, size_t>> all_shaders = {
    {"cifar_conv2d", {src_shaders_spv_cifar_conv2d_spv, src_shaders_spv_cifar_conv2d_spv_len}},
    {"cifar_linear", {src_shaders_spv_cifar_linear_spv, src_shaders_spv_cifar_linear_spv_len}},
    {"cifar_maxpool2d", {src_shaders_spv_cifar_maxpool2d_spv, src_shaders_spv_cifar_maxpool2d_spv_len}},
    {"cifar_sparse_conv2d", {src_shaders_spv_cifar_sparse_conv2d_spv, src_shaders_spv_cifar_sparse_conv2d_spv_len}},
    {"cifar_sparse_linear", {src_shaders_spv_cifar_sparse_linear_spv, src_shaders_spv_cifar_sparse_linear_spv_len}},
    {"cifar_sparse_maxpool", {src_shaders_spv_cifar_sparse_maxpool_spv, src_shaders_spv_cifar_sparse_maxpool_spv_len}},
    {"hello_vector_add", {src_shaders_spv_hello_vector_add_spv, src_shaders_spv_hello_vector_add_spv_len}},
    {"tmp_add_base", {src_shaders_spv_tmp_add_base_spv, src_shaders_spv_tmp_add_base_spv_len}},
    {"tmp_add_base_v2_16", {src_shaders_spv_tmp_add_base_v2_16_spv, src_shaders_spv_tmp_add_base_v2_16_spv_len}},
    {"tmp_add_base_v2_32", {src_shaders_spv_tmp_add_base_v2_32_spv, src_shaders_spv_tmp_add_base_v2_32_spv_len}},
    {"tmp_add_base_v2_64", {src_shaders_spv_tmp_add_base_v2_64_spv, src_shaders_spv_tmp_add_base_v2_64_spv_len}},
    {"tmp_global_exclusive_scan",
     {src_shaders_spv_tmp_global_exclusive_scan_spv, src_shaders_spv_tmp_global_exclusive_scan_spv_len}},
    {"tmp_global_exclusive_scan_v2_16",
     {src_shaders_spv_tmp_global_exclusive_scan_v2_16_spv, src_shaders_spv_tmp_global_exclusive_scan_v2_16_spv_len}},
    {"tmp_global_exclusive_scan_v2_32",
     {src_shaders_spv_tmp_global_exclusive_scan_v2_32_spv, src_shaders_spv_tmp_global_exclusive_scan_v2_32_spv_len}},
    {"tmp_global_exclusive_scan_v2_64",
     {src_shaders_spv_tmp_global_exclusive_scan_v2_64_spv, src_shaders_spv_tmp_global_exclusive_scan_v2_64_spv_len}},
    {"tmp_local_inclusive_scan",
     {src_shaders_spv_tmp_local_inclusive_scan_spv, src_shaders_spv_tmp_local_inclusive_scan_spv_len}},
    {"tmp_local_inclusive_scan_v2_16",
     {src_shaders_spv_tmp_local_inclusive_scan_v2_16_spv, src_shaders_spv_tmp_local_inclusive_scan_v2_16_spv_len}},
    {"tmp_local_inclusive_scan_v2_32",
     {src_shaders_spv_tmp_local_inclusive_scan_v2_32_spv, src_shaders_spv_tmp_local_inclusive_scan_v2_32_spv_len}},
    {"tmp_local_inclusive_scan_v2_64",
     {src_shaders_spv_tmp_local_inclusive_scan_v2_64_spv, src_shaders_spv_tmp_local_inclusive_scan_v2_64_spv_len}},
    {"tmp_single_radixsort_warp16",
     {src_shaders_spv_tmp_single_radixsort_warp16_spv, src_shaders_spv_tmp_single_radixsort_warp16_spv_len}},
    {"tmp_single_radixsort_warp32",
     {src_shaders_spv_tmp_single_radixsort_warp32_spv, src_shaders_spv_tmp_single_radixsort_warp32_spv_len}},
    {"tmp_single_radixsort_warp64",
     {src_shaders_spv_tmp_single_radixsort_warp64_spv, src_shaders_spv_tmp_single_radixsort_warp64_spv_len}},
    {"tree_build_octree", {src_shaders_spv_tree_build_octree_spv, src_shaders_spv_tree_build_octree_spv_len}},
    {"tree_build_radix_tree",
     {src_shaders_spv_tree_build_radix_tree_spv, src_shaders_spv_tree_build_radix_tree_spv_len}},
    {"tree_edge_count", {src_shaders_spv_tree_edge_count_spv, src_shaders_spv_tree_edge_count_spv_len}},
    {"tree_find_dups", {src_shaders_spv_tree_find_dups_spv, src_shaders_spv_tree_find_dups_spv_len}},
    {"tree_merge_sort", {src_shaders_spv_tree_merge_sort_spv, src_shaders_spv_tree_merge_sort_spv_len}},
    {"tree_morton", {src_shaders_spv_tree_morton_spv, src_shaders_spv_tree_morton_spv_len}},
    {"tree_move_dups", {src_shaders_spv_tree_move_dups_spv, src_shaders_spv_tree_move_dups_spv_len}},
    {"tree_naive_prefix_sum",
     {src_shaders_spv_tree_naive_prefix_sum_spv, src_shaders_spv_tree_naive_prefix_sum_spv_len}},
};

}  // namespace shaders

}  // namespace vulkan