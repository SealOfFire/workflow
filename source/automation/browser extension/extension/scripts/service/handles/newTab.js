
const newTab = {
    run: (data) => {
        chrome.tabs.create({ url: "https://www.baidu.com" })
    }
}
