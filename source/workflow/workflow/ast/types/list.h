#pragma once
#include <vector>
#include "object.h"

namespace workflow::ast::types {
    /// <summary>
    /// 
    /// </summary>
    class SHARED_LIB_API List : public Object {
    public:
        static constexpr const char* className = CLASS_NAME_LIST;

        List();
        ~List();

        virtual string getClassName() const;

        virtual string toString();

        /// <summary>
        /// 添加数据
        /// </summary>
        void append(Object* item);

        size_t count();

        Object* elementAt(size_t index);

        void insert(size_t index, Object* item);

        void remove(Object* item);

        void removeAt(size_t index);

        static List* create();

    protected:
        std::vector<Object*> value;

    };
}