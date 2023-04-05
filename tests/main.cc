// Copyright 2006, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
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


#include "gtest/gtest.h"
#include "base/c_types_def.h"

BEGIN_C_DECLS

#if defined(WIN32)
#include <Windows.h>
LARGE_INTEGER freq;
LARGE_INTEGER start;

int64_t int64_muldiv(int64_t value, int64_t numer, int64_t denom) {
  int64_t q = value / denom;
  int64_t r = value % denom;
  return q * numer + r * numer / denom;
}

uint64_t time_platform_now_ms(void) {
  uint64_t now;
  LARGE_INTEGER qpc_t;
  QueryPerformanceCounter(&qpc_t);
  now = int64_muldiv(qpc_t.QuadPart - start.QuadPart, 1000000000, freq.QuadPart);
  return now / 1000000;
}


#else defined(__unix)


#endif

END_C_DECLS

GTEST_API_ int main(int argc, char** argv) {
  printf("Running main() from gtest_main.cc\n");
  testing::InitGoogleTest(&argc, argv);

#if defined(WIN32)
  memset(&freq, 0x0, sizeof(LARGE_INTEGER));
  memset(&start, 0x0, sizeof(LARGE_INTEGER));
  QueryPerformanceFrequency(&freq);
  QueryPerformanceCounter(&start);
#else defined(__unix)

#endif

  RUN_ALL_TESTS();
  return 0;
}
