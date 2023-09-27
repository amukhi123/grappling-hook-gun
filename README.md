# Grappppling Hook Gun

## Description

In this project, I created a grappling hook gun. The player is able to press the 'E' key and deploy the grappling hook. The grappling hook moves the player in the direction of where the grappling hook landed. Once the player reaches the target position the player will fall. If the player hits an obstacle before reaching the target position the player will also fall. There is also a custom map generation script that uses a PNG file. This PNG file contains three colours, black is used to generate a floor tile and a roof tile, these tiles are also spawned to every other colour, white is used to generate wall tiles from the floor to the roof and lastly blue which is used to spawn the player at a particular tile. Additionally, the player is able to sprint using shift, move around using WASD and control rotation using the arrow keys. I also added a debug mode (which can be enabled by pressing the 'F' key) to help diagnose and better visualize problems that arose during the implementation of the grappling hook gun.

## Controls

WASD -> Movement
<br>Arrow Keys -> Rotation
<br>E -> Deploy grappling hook
<br>Left Shift -> Sprint
<br>F -> Enable debug mode

## Gallery

### **Click the thumbnail to play the video**

[![Grappling Hook Gun Implementation Showcase](https://img.youtube.com/vi/f_KirG8yoEI/0.jpg)](https://youtu.be/f_KirG8yoEI)

## How to Run

1. Clone the repository
2. Launch premake-VisualStudio.bat
3. Click on the solution file that was generated (grappling-hook-gun.sln, or parent-directory-name.sln)
4. Build and run project

## Tech Stack

Made using C++, raylib and git.

## Resources

[Cube Textures](https://piiixl.itch.io/textures)
<br>[Crosshair](https://kenney-assets.itch.io/crosshair-pack)
<br>[Music](https://opengameart.org/content/we-are-prophet-happy-energetic-tune)
