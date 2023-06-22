/**
 * 通过元素属性查找元素
 */
commands["find"] = (data) => {
    console.log("find.js", "in", data);

    const cacheId = "temp";

    function createSelector(attribute) {
        let selector = attribute.Tag;
        if (attribute.HasId && attribute.Id !== "") {
            selector += `[id='${attribute.Id}']`
        }
        if (attribute.HasName && attribute.Name !== "") {
            selector += `[name='${attribute.Name}']`
        }
        if (attribute.HasClassName && attribute.ClassName !== "") {
            selector += `[class='${attribute.ClassName}']`
        }
        // TODO 添加更多属性
        return selector
    }

    let attribute = data.Attribute;
    let selector = "body";
    while (true) {
        console.log("find.js", "attribute", attribute);
        selector += ">" + createSelector(attribute)
        if (attribute.Children.length > 0) {
            attribute = attribute.Children[0];
        }
        else {
            break;
        }
    }

    console.log("find.js", "selector", selector);

    //const select = "body> div";
    //document.body.querySelector("body > div[id='wrapper']");
    //document.body.querySelector("body > div[class='wrapper_new wrapper_l']");
    //document.body.querySelector("body > div[id='wrapper'][class='wrapper_new wrapper_l']");
    const element = document.body.querySelector(selector);
    console.log("find.js", "element", element);
    if (element == null) {
        // 没找到元素
        console.log("find.js", "element", "没找到元素");
        data.Success = false;
        data.Error = { Message: "没找到元素" };
    }
    else {
        // 元素添加到缓存中
        console.log("find.js", "element", "找到元素");
        elementCache[cacheId] = element;
        data.Success = true;
    }

    //data.Success = true;
    console.log("find.js", "out", data);
    return data;
}

document.body.querySelector("body > div[id='wrapper']");