<!DOCTYPE HTML>
<html>
<head>

	<title>Arduino</title>

 	<!-- Inclui as etiquetas -->
 	<?php include_once('lib/etiquetasConfig.inc'); ?>

	<!-- Inclui as folhas e arquivos de estilo -->
	<?php include_once('lib/styleConfig.inc'); ?>

	<!-- Inclui os scripts Javascript -->
	<?php include_once('lib/scriptConfig.inc'); ?>

</head>
<body>

	<div class="row">
		<?php include_once('obj/navbarLateral.inc'); ?>

		<div style="z-index: -1;" class="col-md-3"></div>

		<div class="col-md-9">
			<p>Luminosidade: 
			<?php
				include 'class/PhpSerial.php';

				// Inicia classe
				$serial = new PhpSerial;

				// Setar arduino serial
				$serial->deviceSet("COM5");

				// Abre pra ler/escrever informações
				$serial->deviceOpen();

				// Leitura de portas
				$read = $serial->readPort();

				// Pega posição da palavra luz e lê a informação 6 caracteres depois, mostrando na tela
				$pos = strpos($read, 'luz');
				$value = substr($read, $pos + 6, 3);

				echo $value;

				// Fecha porta
				$serial->deviceClose();
			?>
			</p>
		</div>
	</div>

</body>
</html>