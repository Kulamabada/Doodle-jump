# Doodle-jump

The game was was made using SDL2 and C++.

The player controls a doodle which automatically jumps off platforms and tries to
avoid falling. The goal is to reach the highest heights and get the biggest score.
The game is infinite. The camera moves up with a player.

There is shown both the distance the player passed and the number of platforms.

The player can move a doodle using left and right arrow keyboard buttons. The
doodle jumps automatically off any platform beneath it. The player can shoot a projectile by
pressing the left mouse button (the projectile is launched in the direction of the
mouse cursor). The projectile moves linearly with a constant speed and passes through platforms.

Some platforms contain enemies spawned on them. An enemy could be killed
by shooting or jumping on it, but any other intersection with the enemy would kill the player.
Some platforms are fake. The player would fall through if tries to jump off it.

The level consists of platforms. They spawn on a random distance from
each other. The player can pass through the bottom side of the platform.
If the player goes out the left or right side, they appear on the opposite side.
The same mechanic stands for projectiles.

The player has multiple “lifes” (can fall 5 times). “Life” means the ability to continue the game if you fall. After losing a life, the player is launched back to the lowest platform. When the player runs out of “lifes”, falling leads to “game over”. The player loses when falls down (out of the screen) or gets killed by the enemy.
The game is restarted after it’s over.

There is “auto-shooting” ability. It lasts for 20 seconds. If the enemy appears on a screen, the player will automatically shoot it.
