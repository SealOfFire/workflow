/**
 * 选取元素
 */
// TODO 可删除
commands["pickUp"] = (data) => {
    console.log("pickUp.js", "in", data);
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
        console.log("pickUp.js", element);
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
        // 遍历父元素
        parentElement = element;
        allAttr = null;
        while (true) {
            console.log("parentElement", parentElement);
            attribute = {
                ElementType: 2, // 2是html元素
                Values:
                {
                    tag: parentElement.tagName,
                    /*innerHTML: parentElement.innerHTML*/
                },
                Parent: null,
                Children: []
            }
            for (let i = 0; i < parentElement.attributes.length; i++) {
                var attr = parentElement.attributes[i];
                attribute.Values[attr.name] = attr.value
            }

            if (allAttr == null) {
                allAttr = attribute
            }
            else {
                attribute.Children.push(allAttr);
                allAttr = attribute;
            }

            console.log("parentElement", allAttr);
            // 没有父元素的时候返回
            //console.log("parentElement", element.parentNode.tagName);
            if (parentElement.parentNode.tagName === "BODY") {
                break;
            }

            parentElement = parentElement.parentNode;
        }

        console.log("parentElement", allAttr);

        // 返回元素
        data.Attribute = allAttr;
        data.Success = true;

    }
    console.log("pickUp.js", "out", data);
    return data;
}
