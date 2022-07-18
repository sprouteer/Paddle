// Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "paddle/phi/kernels/as_real_kernel.h"

#include "paddle/phi/core/dense_tensor.h"
#include "paddle/phi/core/tensor_utils.h"
#include "paddle/phi/kernels/funcs/for_range.h"

namespace phi {
template <typename T, typename Context>
void AsRealKernel(const Context& ctx, const DenseTensor& x, DenseTensor* out) {
  ctx.template Alloc<T>(out);
  auto out_dims_original = out->dims();
  Copy(ctx, x, ctx.GetPlace(), false, out);
  out->Resize(out_dims_original);  // restored the shape.
  out->set_type(
      paddle::experimental::CppTypeToDataType<T>::Type());  // restored the
                                                            // dtype.
}

}  // namespace phi