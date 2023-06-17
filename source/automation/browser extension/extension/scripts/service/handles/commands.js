importScripts('handles/newTab.js');
importScripts('handles/hover.js');
importScripts('handles/pickUp.js');
importScripts('handles/fromPoint.js');
importScripts('handles/highlight.js');

const commands = {
    newTab: (data) => { return newTab.run(data); },
    hover: (data) => { return hover.run(data); }, // 鼠标悬浮在元素上高亮元素
    pickUp: (data) => { return pickUp.run(data); }, // 鼠标坐标获取元素
    fromPoint: (data) => { return fromPoint.run(data); },
    highlight: (data) => { return highlight.run(data); },
}