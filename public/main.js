var database = firebase.database();
const data1 = document.getElementById('CheckBTN')
const data2 = document.getElementById('TTL')
const data3 = document.getElementById('LedBTN')
var htmlData = '';
        

    var dataget = database.ref('DataCheck');
    dataget.on('value', (snapshot) => {
    var data = snapshot.val();
    var btn = data.connect;
    
    if (btn === "0") {
        htmlData = `
          <div>
          <h3>Đã kết nối</h3>
          </div>
        `;

            var dataget = database.ref('DataButton');
            dataget.on('value', (snapshot) => {
            var data = snapshot.val();
            var btn1 = data.test;
            var btn3 = data.timer;

            if (btn1 === "0") { 
                Checkled();
                htmlData1 = `
                <button onclick="onled();">Tắt</button>
                <h4>Đếm Ngược Thời Gian Tự Khởi Động Lại</h4>
                <h4 style="color: red;">Còn Lại: ${btn3} Giây</h4>
                `
            } else if (btn1 === "1") { 
                Checkled();
                htmlData1 = `
                <button onclick="offled();">Bật</button>
                <h4>Đếm Ngược Thời Gian Tự Khởi Động Lại</h4>
                <h4 style="color: red;">Còn Lại: ${btn3} Giây</h4>
                `
            } else {
                htmlData1 = '';
            }
            data2.innerHTML = htmlData1;
            });

    }

    else if (btn === "1") {
        htmlData = ``;
        data2.innerHTML = '';
    }
    
    data1.innerHTML = htmlData;
    });

    database.ref('DataCheck').set({
        "connect": "1"
        });
        Check();

function Check() {
    database.ref('DataCheck').set({
    "connect": "1"
    });
    data1.innerHTML = `
    <div>
    <h3>Đang kết nối...</h3>
    </div>
    `;
    data3.innerHTML = '';
}


function onled() {
    database.ref('DataButton').update({
        "test": "1"
    });
}

function offled() {
    database.ref('DataButton').update({
        "test": "0"
    });
}

function Checkled() {
    var dataget = database.ref('DataPlus');
    dataget.on('value', (snapshot) => {
    var data = snapshot.val();
    var btn2 = data.test;

        if (btn2 === "0") {
            htmlData2 = `
            <div>
            <img src="ledon.png" alt="">
            </div>
            `;
            } else if (btn2 === "1") {
                htmlData2 = `
                <div>
                <img src="ledoff.png" alt="">
                </div>
                `;
            } 
            data3.innerHTML = htmlData2;
            });
}

function Manual() {
    database.ref('But102').set({
        "data": "0"
    });
}

function Runloop() {
    database.ref('But102').set({
        "data": "1"
    });
}
