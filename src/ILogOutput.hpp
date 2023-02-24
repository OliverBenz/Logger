#pragma once

namespace Logging {

//! Defines what functionality a log output has to define.
class ILogOutput {
protected:
	ILogOutput() = default;
    ILogOutput(ILogOutput&& other) = default;
    ILogOutput(const ILogOutput& other) = default;

    ILogOutput& operator=(ILogOutput&& other) = default;
    ILogOutput& operator=(ILogOutput const& other) = default;

public:
    virtual ~ILogOutput() = default;

	virtual void Write() = 0; 
};

}