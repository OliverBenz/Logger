#pragma once

namespace Logging {

//! Defines what functionality a log output has to define.
class ILogOutput {
public:
	ILogOutput() = delete;
	~ILogOutput() = delete;

	virtual void Write() = 0; 
};

}