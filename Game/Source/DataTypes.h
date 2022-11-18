#pragma once

//typedef fw::Vec2 Vec2; //Old way
//typedef unsigned int uint32; //Used to change the name to show the size in bits

using Vec2 = fw::Vec2; //Used to stop you from needing to type in fw every time

using Mesh = fw::Mesh;

using ShaderProgram = fw::ShaderProgram;

using string = std::string;

using VertexFormat = fw::VertexFormat;

using Texture = fw::Texture;

using json = nlohmann::json;

using Camera = fw::Camera;

using SpriteSheet = fw::SpriteSheet;

using SpriteInfo = fw::SpriteInfo;

using FlipBook = fw::FlipBook;