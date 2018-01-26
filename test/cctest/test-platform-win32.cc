// Copyright 2006-2008 the V8 project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include "src/base/platform/platform.h"
#include "test/cctest/cctest.h"

using OS = v8::base::OS;

namespace v8 {
namespace internal {

TEST(OSReserveMemory) {
  size_t mem_size = 0;
  void* mem_addr = OS::ReserveAlignedRegion(1 * MB, OS::AllocateAlignment(),
                                            GetRandomMmapAddr(), &mem_size);
  CHECK_NE(0, mem_size);
  CHECK_NOT_NULL(mem_addr);
  size_t block_size = 4 * KB;
  CHECK(OS::CommitRegion(mem_addr, block_size, false));
  // Check whether we can write to memory.
  int* addr = static_cast<int*>(mem_addr);
  addr[KB - 1] = 2;
  CHECK(OS::UncommitRegion(mem_addr, block_size));
  OS::ReleaseRegion(mem_addr, mem_size);
}

}  // namespace internal
}  // namespace v8
