  const char* html = R"=====(
  <!DOCTYPE html><html><head><meta charset='UTF-8'>";
  "<title> etanol sensor test </title>";
  "</head><body>";
  "<h1>Alkohol measurement</h1>";
  "<p>Value:</p>";
  "<h2>" + String(promil,2) + "‰</h2>";

  <button onpointerdown="go(255,255)" onpointerup="go(0,0)">PRZÓD</button>
  <button onpointerdown="go(-255,-255)" onpointerup="go(0,0)">TYŁ</button>
  <button onpointerdown="go(90,255)" onpointerup="go(0,0)">LEWO</button>
  <button onpointerdown="go(255,90)" onpointerup="go(0,0)">PRAWO</button>

  <script>
  function go(l, r) {
    fetch("/ruch?l=" + l + "&r=" + r);
  }

  async function odswiez() {
    let odpowiedz = await fetch("/pomiar");
    let tekst = await odpowiedz.text();
    document.getElementById("v").innerText = tekst + "‰";
  }

  setInterval(odswiez, 1000);
  </script>
  </body></html>
  )=====";