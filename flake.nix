{
  description = "Raylib development environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self , nixpkgs ,... }: let
    system = "x86_64-linux";
  in {
    devShells."${system}".default = let
      pkgs = import nixpkgs {
        inherit system;
      };
    in pkgs.mkShell {
      packages = [
        pkgs.raylib
        pkgs.tcl
        pkgs.tclPackages.tclx

        # Uncomment the line below if you want to build Raylib with web support
        # pkgs.emscripten
      ];
    };
  };
}
