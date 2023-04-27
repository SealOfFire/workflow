#include "activity.h"

using namespace workflow::ast::executors;
using namespace workflow::ast::statements;

namespace workflow::framework::activities {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    void Activity::execute(Context* context) {
        // TODO 执行前延迟

        // TODO错误执行
        try {
            // 计算表达式
            for (auto [name, expr] : this->parameters) {
                Object* value = expr->run(context);
                // 表达式结果传入到python中
            }

            this->executeActivity(context);
        }
        catch (int i) {

        }

        // TODO 执行后延迟
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    void Activity::executeActivity(Context* context) {

    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    std::string Activity::toScriptCode(Context* context) {
        std::string indent(context->indentCount * context->indentLevel, ' ');
        return indent + "Activity" + context->newline;
    }
}