/*
 * service_impl.h
 * -------------------------------------------------------------------------
 * Abstract base class for service-specific implementation classes.
 * -------------------------------------------------------------------------
 *
 * Copyright (c) 2011, Tarick Bedeir.
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

#ifndef S3_SERVICES_IMPL_H
#define S3_SERVICES_IMPL_H

#include <fstream>
#include <string>
#include <boost/function.hpp>
#include <boost/smart_ptr.hpp>

namespace s3
{
  namespace base
  {
    class request;
  }

  namespace services
  {
    typedef boost::function2<void, base::request *, bool> signing_function;

    class impl
    {
    public:
      typedef boost::shared_ptr<impl> ptr;

      virtual const std::string & get_header_prefix() = 0;
      virtual const std::string & get_header_meta_prefix() = 0;
      virtual const std::string & get_url_prefix() = 0;
      virtual const std::string & get_xml_namespace() = 0;

      virtual bool is_multipart_download_supported() = 0;
      virtual bool is_multipart_upload_supported() = 0;

      virtual const std::string & get_bucket_url() = 0;

      virtual const signing_function & get_signing_function() = 0;

    protected:
      static void open_private_file(const std::string &file, std::ifstream *f);
      static void open_private_file(const std::string &file, std::ofstream *f);
    };
  }
}

#endif