exports.createTable = async (datas) => {
    let text = "<ul>";
    for (var i = 0; i < datas.length; i++) {
        text += "<li>" + datas[i] + "</li>";
    }
    text += "</ul>";
    return text;
}