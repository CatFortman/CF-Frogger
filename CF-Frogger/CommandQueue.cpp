#include "CommandQueue.h"
namespace GEX {

	void CommandQueue::push(const Command & command)
	{
		_queue.push(command);
	}

	Command CommandQueue::pop()
	{
		auto result = _queue.front();
		_queue.pop();
		return result;
	}

	bool CommandQueue::isEmpty() const
	{
		return _queue.empty();
	}

}


