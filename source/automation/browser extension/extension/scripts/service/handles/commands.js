//importScripts('handles/hover.js');
//importScripts('handles/pickUp.js');
importScripts('handles/find.js');
importScripts('handles/fromPoint.js');
importScripts('handles/highlight.js');
importScripts('handles/newTab.js');

const commands = {
    find: (data) => { return find.run(data); }, // 通过元素属性查找元素
    //hover: (data) => { return hover.run(data); }, // 鼠标悬浮在元素上高亮元素
    //pickUp: (data) => { return pickUp.run(data); }, // 鼠标坐标获取元素
    fromPoint: (data) => { return fromPoint.run(data); },
    highlight: (data) => { return highlight.run(data); },
    newTab: (data) => { return newTab.run(data); },
}