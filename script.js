const apiKey = "19b5322c249a5921e00463847d068d2f";

function displayResult(data) {
    const temp = data.main.temp;
    const weather = data.weather[0].main.toLowerCase();
    const clouds = data.clouds.all;
    const sunrise = data.sys.sunrise;
    const sunset = data.sys.sunset;

    const sunriseTime = new Date(sunrise * 1000).toLocaleTimeString();
    const sunsetTime = new Date(sunset * 1000).toLocaleTimeString();

    let condition = "";
    let color = "";

    // 📸 Smart photography logic
    if (weather.includes("rain") || weather.includes("storm")) {
        condition = "❌ Bad for photography (Rain/Storm)";
        color = "red";
    }
    else if (clouds > 80) {
        condition = "⚠️ Flat lighting (Too cloudy)";
        color = "orange";
    }
    else if (clouds > 30) {
        condition = "✅ Excellent for portraits (Soft light)";
        color = "green";
    }
    else {
        condition = "🔥 Great but harsh light (Use shadows)";
        color = "gold";
    }

    document.getElementById("weatherResult").innerHTML = `
        <h3>${data.name}</h3>
        <p>🌡 Temp: ${temp}°C</p>
        <p>🌤 Condition: ${weather}</p>
        <p style="color:${color}; font-weight:bold;">${condition}</p>
        
        <hr>
        <p>🌅 Golden Hour:</p>
        <p>Morning: ${sunriseTime}</p>
        <p>Evening: ${sunsetTime}</p>
    `;
}

// 🔍 Search by city
function getWeather() {
    const city = document.getElementById("city").value;

    if (!city) {
        alert("Enter location");
        return;
    }

    fetch(`https://api.openweathermap.org/data/2.5/weather?q=${city}&appid=${apiKey}&units=metric`)
        .then(res => res.json())
        .then(displayResult)
        .catch(() => {
            document.getElementById("weatherResult").innerHTML = "Error fetching data";
        });
}

// 📍 Auto location
function getLocationWeather() {
    navigator.geolocation.getCurrentPosition(position => {
        const lat = position.coords.latitude;
        const lon = position.coords.longitude;

        fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${lon}&appid=${apiKey}&units=metric`)
            .then(res => res.json())
            .then(displayResult);
    });
}
