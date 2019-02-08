#pragma once

#include "xmrstak/misc/environment.hpp"
#include "xmrstak/params.hpp"
#include "xmrstak/backend/amd/minethd.hpp"
#include "xmrstak/backend/nvidia/minethd.hpp"

#include <thread>
#include <atomic>
#include <vector>
#include <string>
#include "iBackend.hpp"
#include <iostream>

namespace xmrstak
{

	struct plugin
	{
		enum BackendType {
			AMD,
			NVIDIA
		};
		plugin() = default;

		std::vector<iBackend*>* startBackend(uint32_t threadOffset, miner_work& pWork, environment& env, BackendType libType, const std::string backendName)
		{
			printer::inst()->print_msg(L0, "INFO: trying to load backend %s.", backendName.c_str());

			if (libType == AMD) {
				using namespace xmrstak::amd;

				return minethd::xmrstak_start_backend(threadOffset, pWork, env);
			}
			else if (libType == NVIDIA) {
				using namespace nvidia;

				return minethd::xmrstak_start_backend(threadOffset, pWork, env);
			}

			std::vector<iBackend*>* pvThreads = new std::vector<iBackend*>();
			return pvThreads;
		}
	};

} // namespace xmrstak
