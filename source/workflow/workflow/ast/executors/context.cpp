#include "context.h"
#include "../exceptions/keyNotFoundException.h"
#include "../exceptions/nullReferenceException.h"
#include "../modules/module.h"

namespace workflow::ast::executors {

	types::Object* Context::getLocalVariable(std::string name) {
		if (this->currentModule == nullptr) {
			// 模块不存在
			throw ast::exceptions::NullReferenceException(this, "module");
		}

		if (this->currentModule->variables.count(name) == 0) {
			// 变量不存在
			throw ast::exceptions::KeyNotFoundException(this, name);
		}

		return this->currentModule->variables[name];
	}

}