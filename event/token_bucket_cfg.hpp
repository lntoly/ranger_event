// Copyright (c) 2015, RangerUFO
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// 
// * Neither the name of ranger_event nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef RANGER_EVENT_TOKEN_BUCKET_CFG_HPP
#define RANGER_EVENT_TOKEN_BUCKET_CFG_HPP

#include <memory>

struct ev_token_bucket_cfg;

namespace ranger { namespace event {

	class token_bucket_cfg : public std::enable_shared_from_this<token_bucket_cfg>
	{
	public:
		~token_bucket_cfg();

		token_bucket_cfg(const token_bucket_cfg&) = delete;
		token_bucket_cfg& operator = (const token_bucket_cfg&) = delete;

		static std::shared_ptr<token_bucket_cfg> create(size_t read_rate, size_t read_burst, size_t write_rate, size_t write_burst, float period = 0.0f);

#ifdef RANGER_EVENT_INTERNAL
	public:
#else
	private:
#endif	// RANGER_EVENT_INTERNAL
		token_bucket_cfg(size_t read_rate, size_t read_burst, size_t write_rate, size_t write_burst, float period);

		ev_token_bucket_cfg* _ev_token_bucket_cfg() const { return m_cfg; }

	private:
		ev_token_bucket_cfg* m_cfg;
	};

} }

#endif	// RANGER_EVENT_TOKEN_BUCKET_CFG_HPP
