#pragma once
#include "exception.h"

namespace workflow::ast::exceptions {

	/// <summary>
	/// 
	/// </summary>
	class SHARED_LIB_API DataTypeException : public Exception {
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="object"></param>
		/// <param name="message"></param>
		DataTypeException(void* object, std::string name, std::string correctType, std::string errorType);

		virtual string what() const;

	protected:
		std::string name;
		std::string correctType;
		std::string errorType;
	};
}