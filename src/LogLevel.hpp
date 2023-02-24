#pragma once

namespace Logging {

enum class LogLevel {
	Any      = 000,
	Info     = 100,
	Debug    = 200,
	Warning  = 300,
	Error    = 400,
	Critical = 500
};

}