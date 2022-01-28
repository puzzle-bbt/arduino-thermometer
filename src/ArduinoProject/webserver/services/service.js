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
    let title = "<td class='headRow'>Temperatur</td>" +
        "<td class='headRow'>Humidity</td>" +
        "<td class='headRow'>Heat index</td>";
    for (var i = datas.length - 1; i != -1 ; i--) {
        let temp = datas[i].split(",")[0];
        let hum = datas[i].split(",")[1];
        let hi = datas[i].split(",")[2];
        text += "<td class='listItem'>" + temp + "</td>" +
            "<td class='listItem'>" + hum + "</td>" +
            "<td class='listItem'>" + hi + "</td>" +
            "</tr>";
    }
    table += title + text + "</table>";

    return table;
}
