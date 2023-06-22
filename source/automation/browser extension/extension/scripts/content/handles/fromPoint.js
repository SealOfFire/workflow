/**
 * 根据鼠标位置获取元素
 */
commands["fromPoint"] = (data) => {
    console.log("fromPoint.js", "in", data);
    // 坐标 data.Position.X, data.Position.Y
    // 颜色 data.Highlight.Color
    // 持续时间 data.Highlight.Duration
    const element = document.elementFromPoint(data.Position.X, data.Position.Y);
    //const element = document.elementsFromPoint(data.Position.X, data.Position.Y); // todo
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

        /*
        // 返回元素
        data.Attribute = {
            ElementType: 2, // 2是html元素
            Values:
            {
                tag: element.tagName,
                //innerHTML: element.innerHTML,
                cacheId: cacheId,
            },
            Children: []
        };
        //let values = { tag: element.tagName };
        for (let i = 0; i < element.attributes.length; i++) {
            var attr = element.attributes[i];
            data.Attribute.Values[attr.name] = attr.value
        }
        */
        // 遍历父元素
        parentElement = element;
        allAttr = null;
        let index = 0;
        while (index < data.ParentDepth || data.ParentDepth < 0) {
            index++;
            console.log("parentElement", parentElement);
            attribute = {
                ElementType: 2, // 2是html元素
                CacheId: cacheId,
                tag: parentElement.tagName,
                Values: {},
                Parent: null,
                Children: []
            }

            if (parentElement.id != undefined) {
                attribute.name = parentElement.id;
            }

            if (parentElement.name != undefined) {
                attribute.name = parentElement.name;
            }

            if (parentElement.className != undefined) {
                attribute.className = parentElement.className;
            }

            if (parentElement.href != undefined) {
                attribute.title = parentElement.title;
            }

            if (parentElement.href != undefined) {
                attribute.href = parentElement.href;
            }

            if (parentElement.type != undefined) {
                attribute.type = parentElement.type;
            }

            for (let i = 0; i < parentElement.attributes.length; i++) {
                var attr = parentElement.attributes[i];
                attribute.Values[attr.name] = attr.value
            }

            console.log("parentElement", 8);
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


        // 元素添加到缓存中
        elementCache[cacheId] = element;
        allAttr.CacheId = cacheId;
        data.Attribute = allAttr;
        data.Success = true;

    }
    console.log("fromPoint.js", "out", data);
    return data;
}
