/**
 * 鼠标悬浮在元素上的时候高亮元素
 */
// TODO 可删除
commands["hover"] = (data) => {
    console.log("hover.js", "in", data);
    // 坐标 data.Position.X, data.Position.Y
    // 颜色 data.Highlight.Color
    // 持续时间 data.Highlight.Duration
    const element = document.elementFromPoint(data.Position.X, data.Position.Y);
    if (element == null) {
        // 没找到元素
        data.Success = false;
        data.Error = { Message: "没有找到元素" }
    }
    else {
        // 找到元素
        console.log("hover.js", element);
        // 获取元素的位置和大小
        const rect = element.getBoundingClientRect()
        console.log(rect)
        /*
        data.BoundingRectangle = {
            x: 0,
            y: 0,
            width: rect.width,
            height: rect.height
        };
        */

        // 返回元素
        data.Attribute = {
            ElementType: 2, // 2是html元素
            Values:
            {
                tag: element.tagName,
                innerHTML: element.innerHTML
            },
            Children: []
        };
        //let values = { tag: element.tagName };
        for (let i = 0; i < element.attributes.length; i++) {
            var attr = element.attributes[i];
            data.Attribute.Values[attr.name] = attr.value
        }

        // 给元素添加高亮边框
        element.classList.add("highlight");
        setTimeout(() => {
            element.classList.remove("highlight");
        }, data.Highlight.Duration);

        data.Success = true;

    }
    console.log("hover.js", "out", data);
    return data;
}
