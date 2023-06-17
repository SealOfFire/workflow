/**
 * 高亮缓存中的元素
 */
commands["highlight"] = (data) => {
    console.log("highlight.js", "in", data);

    const element = elementCache["temp"];
    if (element == null) {
        // 没找到元素
        data.Success = false;
        data.Error = { Message: "没有找到元素" }
    }
    else {
        // 找到元素
        console.log("fromPoint.js", element);
        // 获取元素的位置和大小

        // 给元素添加高亮边框
        element.classList.add("highlight");
        setTimeout(() => {
            element.classList.remove("highlight");
        }, data.Highlight.Duration);

        // 清除缓存
        elementCache["temp"] = element;

        data.Success = true;

    }
    console.log("highlight.js", "out", data);
    return data;
}
