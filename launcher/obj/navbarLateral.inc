<!-- Navbar -->

<div style="height: 100%; position: absolute;" class="col-md-3 navbar-dark bg-dark">
  <h2 style="text-align: center; color: #FFFFFF; padding-top: 18px;"><img src="images/logo.png"/>&nbsp;&nbsp;Arduino Mega</h2>
  <hr/><br/>
  <ul style="padding-left: 20px;" class="navbar-nav">
    <h4 style="color: #FFFFFF;">Sensores</h3>
    <li class="nav-item"><a id="luz" class="nav-link" href="sensorLuz.php">Luz</a></li>
    <li class="nav-item"><a id="temp" class="nav-link" href="sensorTemperatura.php">Temperatura</a></li>
    <li class="nav-item"><a id="umidade" class="nav-link" href="sensorUmidade.php">Umidade</a></li>
  </ul>
  <ul style="padding-left: 20px; padding-top: 20px;" class="navbar-nav">
    <h4 style="color: #FFFFFF;">Sobre</h3>
    <li class="nav-item"><a id="info" class="nav-link" href="index.php">Informações</a></li>
    <li class="nav-item"><a id="config" class="nav-link" href="config.php">Configurações</a></li>
  </ul>
</div>

<script>

    var url = window.location.href;

    //localhost
    if (url == "http://localhost/launcher/sensorLuz.php") {
       $('#luz').addClass('active');
    }
    else if (url == "http://localhost/launcher/sensorTemperatura.php") {
       $('#temp').addClass('active');
    }
    else if (url == "http://localhost/launcher/sensorUmidade.php") {
       $('#umidade').addClass('active');
    }
    else if (url == "http://localhost/launcher/index.php") {
       $('#info').addClass('active');
    }
    else if (url == "http://localhost/launcher/config.php") {
       $('#config').addClass('active');
    }
    else if (url == "http://localhost/launcher/") {
       $('#info').addClass('active');
    }
    else if (url == "http://localhost/launcher/#") {
       $('#info').addClass('active');
    }
    if (url == "localhost/launcher/sensorLuz.php") {
       $('#luz').addClass('active');
    }
    else if (url == "localhost/launcher/sensorTemperatura.php") {
       $('#temp').addClass('active');
    }
    else if (url == "localhost/launcher/sensorUmidade.php") {
       $('#umidade').addClass('active');
    }
    else if (url == "localhost/launcher/index.php") {
       $('#info').addClass('active');
    }
    else if (url == "localhost/launcher/config.php") {
       $('#config').addClass('active');
    }
    else if (url == "localhost/launcher/") {
       $('#info').addClass('active');
    }
    else if (url == "localhost/launcher/#") {
       $('#info').addClass('active');
    }

    //127.0.0.1
    else if (url == "http://127.0.0.1/launcher/sensorLuz.php") {
       $('#luz').addClass('active');
    }
    else if (url == "http://127.0.0.1/launcher/sensorTemperatura.php") {
       $('#temp').addClass('active');
    }
    else if (url == "http://127.0.0.1/launcher/sensorUmidade.php") {
       $('#umidade').addClass('active');
    }
    else if (url == "http://127.0.0.1/launcher/index.php") {
       $('#info').addClass('active');
    }
    else if (url == "http://127.0.0.1/launcher/config.php") {
       $('#config').addClass('active');
    }
    else if (url == "http://127.0.0.1/launcher/") {
       $('#info').addClass('active');
    }
    else if (url == "http://127.0.0.1/launcher/#") {
       $('#info').addClass('active');
    }

    else if (url == "127.0.0.1/launcher/sensorLuz.php") {
       $('#luz').addClass('active');
    }
    else if (url == "127.0.0.1/launcher/sensorTemperatura.php") {
       $('#temp').addClass('active');
    }
    else if (url == "127.0.0.1/launcher/sensorUmidade.php") {
       $('#umidade').addClass('active');
    }
    else if (url == "127.0.0.1/launcher/index.php") {
       $('#info').addClass('active');
    }
    else if (url == "127.0.0.1/launcher/config.php") {
       $('#config').addClass('active');
    }
    else if (url == "127.0.0.1/launcher/") {
       $('#info').addClass('active');
    }
    else if (url == "127.0.0.1/launcher/#") {
       $('#info').addClass('active');
    }

</script>