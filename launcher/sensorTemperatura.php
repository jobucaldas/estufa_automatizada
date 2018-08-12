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
			<p>Temperatura: 
			<?php
				include 'class/PhpSerial.php';

				// Inicia classe
				$serial = new PhpSerial;

				// Setar arduino serial
				$serial->deviceSet("COM5");

				// Abre pra ler/escrever informações
				$serial->deviceOpen();

				// Pega posição da palavra temperatura e lê a informação 6 caracteres depois, mostrando na tela
				$pos = strpos($read, 'temperatura');
				$value = substr($read, $pos + 11 + 3, 3);

				echo $value;

				$serial->deviceClose();
			?>
			</p>
		</div>
	</div>

</body>
</html>