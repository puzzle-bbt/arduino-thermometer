exports.createList = async (datas) => {
    let text = "<ul>";
    for (var i = 0; i < datas.length; i++) {
        text += "<li>" + datas[i] + "</li>";
    }
    text += "</ul>";
    return text;
}

exports.createTable = async (datas) => {
    let table = "<table>";
    let text = "<tr>";
    for (var i = 0; i < datas.length; i++) {
        text += "<td>" + datas[i] + "</td>" + "</tr>";
    }
    table += text + "</table>";
    return table;
}
