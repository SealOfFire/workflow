#include "dataTypeException.h"

namespace workflow::ast::exceptions {

	/// <summary>
	/// 
	/// </summary>
	/// <param name="object"></param>
	/// <param name="message"></param>
	DataTypeException::DataTypeException(void* object, std::string name, std::string correctType, std::string errorType)
		:name(name), correctType(correctType), errorType(errorType),
		Exception(object, ERROR_MESSAGE_DataType) { }

	std::string DataTypeException::what() const {
		return Exception::what() + ":" + this->name + ":" + this->correctType + ":" + this->errorType;
	}
}