#include "container.h"
#include "return.h"

using namespace workflow::ast::executor;
using namespace workflow::ast::statements;

/// <summary>
/// 
/// </summary>
Container::Container() {
}

/// <summary>
/// 
/// </summary>
Container::~Container() {
    this->children.clear();
    this->children.shrink_to_fit();
}

/// <summary>
/// 
/// </summary>
void Container::execute(Context* context) {

    // 遍历方式，顺序遍历，指定下一个组件id遍历
    for (Statement* child : this->children) {
        if (child->getClassName() == CLASS_NAME_BREAK) {
            break;
        }
        else {
            child->run(context);
        }
    }
}

string Container::getClassName() const {
    return Container::className;
}

/// <summary>
/// 
/// </summary>
/// <param name="statement"></param>
void Container::addStatement(Statement* statement) {
    this->children.push_back(statement);
}

/// <summary>
/// 
/// </summary>
/// <param name="context"></param>
/// <returns></returns>
string Container::toScriptCode(Context* context) {

    string indent(context->indentCount * context->indentLevel, ' ');
    string output;

    for (Statement* child : this->children) {
        output += child->toScriptCode(context);
    }

    return output;
}