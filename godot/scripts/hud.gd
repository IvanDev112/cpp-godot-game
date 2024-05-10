extends HUD

func show_game_over():
	show_message("Game Over")

	await $MessageTimer.timeout

	$Message.text = "Dodge the Creeps!"
	$Message.show()

	await get_tree().create_timer(1.0).timeout
	$StartButton.show()