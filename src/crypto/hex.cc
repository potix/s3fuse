/*
 * crypto/hex.cc
 * -------------------------------------------------------------------------
 * Hex encoder (implementation).
 * -------------------------------------------------------------------------
 *
 * Copyright (c) 2012, Tarick Bedeir.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdexcept>

#include "crypto/hex.h"

using std::string;
using std::runtime_error;
using std::vector;

using s3::crypto::hex;

namespace
{
  inline int hex_char_to_int(char c)
  {
    return (c < 'a') ? (c - '0') : (c - 'a' + 10);
  }
}

string hex::encode(const uint8_t *input, size_t size)
{
  const char *HEX = "0123456789abcdef";
  string ret;

  ret.resize(size * 2);

  for (size_t i = 0; i < size; i++) {
    ret[2 * i + 0] = HEX[static_cast<uint8_t>(input[i]) / 16];
    ret[2 * i + 1] = HEX[static_cast<uint8_t>(input[i]) % 16];
  }

  return ret;
}

void hex::decode(const string &input, vector<uint8_t> *output)
{
  if (input.size() % 2)
    throw runtime_error("cannot have odd number of hex characters to decode!");

  output->resize(input.size() / 2);

  for (size_t i = 0; i < output->size(); i++)
    (*output)[i] = 
      hex_char_to_int(input[2 * i + 0]) * 16 +
      hex_char_to_int(input[2 * i + 1]);
}
