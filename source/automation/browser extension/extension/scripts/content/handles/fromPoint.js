/**
 * 根据鼠标位置获取元素
 */
commands["fromPoint"] = (data) => {
    console.log("fromPoint.js", "in", data);
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
        console.log("fromPoint.js", element);
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

        const cacheId = "temp";

        // 返回元素
        data.Attribute = {
            ElementType: 2, // 2是html元素
            Values:
            {
                tag: element.tagName,
                innerHTML: element.innerHTML,
                cacheId: cacheId,
            },
            Children: []
        };
        //let values = { tag: element.tagName };
        for (let i = 0; i < element.attributes.length; i++) {
            var attr = element.attributes[i];
            data.Attribute.Values[attr.name] = attr.value
        }

        // 元素添加到缓存中
        elementCache[cacheId] = element;

        data.Success = true;

    }
    console.log("fromPoint.js", "out", data);
    return data;
}
