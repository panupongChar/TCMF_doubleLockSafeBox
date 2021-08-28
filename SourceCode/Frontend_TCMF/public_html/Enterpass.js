const password_ele = document.getElementById("password");
const status_ele = document.getElementById("hw-status");
app = document.getElementById("app");

function scream(password) {
  return new Promise((resolve, reject) => {
    fetch("http://192.168.43.104:3000/enter_password", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ password :  password }),
    })
      .then((response) => response.text())
      .then((result) => console.log(result))
      .then(() => {resolve(true)})
      .catch((error) => console.log("error", error));
  })
}

let butt = document.getElementById("check");
butt.addEventListener("click", () => {
  console.log("hello");
  fetch("http://192.168.43.104:3000/check" ,{
    method: "GET",
    headers: { "Content-Type": "application/json" },
  })
  .then((data) => data.json())
  .then((data) => { 
    const c = data.check;
    if (data.check == 1) {
    console.log(data.check);
    document.getElementById("hw-status").innerHTML = "AVAILABLE";
    document.getElementById("hw-status").style.color = "#57b846";
  }
  else {
    console.log(data.check);
    alert("Please enter password at hardware state!!!");
  }
})
  .catch((error) => console.log("error na krub",error));
  // if (data.check == 1) {
  //   document.getElementById("hw-status").innerHTML = "AVAILABLE";
  //   document.getElementById("hw-status").style.color = "#57b846";
  // }
  // else {
  //   alert("Please enter password at hardware state!!!")
  // }
});

// function Check() {
//   // document.getElementById("hw-status").innerHTML = "AVAILABLE";
//   // document.getElementById("hw-status").style.color = "#57b846";
//   fetch("http://192.168.43.104:3000/check", {
//       method: "GET",
//       // headers: { "Content-Type": "application/json" },
//   })
//   .then((data) => data.text())
//   console.log(data);
//   if (response.check == 1) {
//     document.getElementById("hw-status").innerHTML = "AVAILABLE";
//     document.getElementById("hw-status").style.color = "#57b846";
//   }
//   else {
//       alert("Please enter password at hardware state!!!")
//   }
// }

// function scream(password) {
//   fetch("http://192.168.43.104:3000/enter_password", {
//     method: "POST",
//     headers: { "Content-Type": "application/json" },
//     body: JSON.stringify({ password :  password }),
//   })
//   .then((response) => response.text())
//   .then((result) => console.log(result))
//   .catch((error) => console.log("error", error));

function login(){
  var status_ele = document.getElementById("hw-status");

  var status = status_ele.innerHTML
  var password = password_ele.value;
  // console.log(password)

  if (password == "") {
    document.getElementById("errormsg").innerHTML = "Can't be blank!!";
  }
  else {
    document.getElementById("errormsg").innerHTML = "";
    console.log(status);
    if (status == "AVAILABLE") {
      scream(password);
      document.getElementById("hw-status").innerHTML = "NOT AVAILABLE";
      document.getElementById("hw-status").style.color = "crimson";
      alert("Enter password successfully!");
    }
    else {
      alert("Please check!!!");
    }
    password_ele.value = "";
    // scream(password);
  }
}
