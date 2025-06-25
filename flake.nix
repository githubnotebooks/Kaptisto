{
  description = "A basic Nix flake providing development shells";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    nixpkgs-unstable.follows = "nixpkgs";
    nixpkgs-stable.url = "github:NixOS/nixpkgs/nixos-25.05";
    nixpkgs-old.url = "github:NixOS/nixpkgs/nixos-24.11";
    nur = { url = "github:nix-community/NUR"; };
  };

  outputs = { self, nixpkgs, nixpkgs-stable, nixpkgs-old, nur, ... }@inputs:
    let
      pkg-settings = rec {
        allowed-unfree-packages = pkg:
          builtins.elem (nixpkgs.lib.getName pkg) [
            "cudnn"
            "libcublas"
          ];
        allowed-insecure-packages = [ "electron-11.5.0" "openssl-1.1.1w" ];
      };

      eachSystem = nixpkgs.lib.genAttrs [ "x86_64-linux" ] (system:
        let
          pkgs = import nixpkgs {
            inherit system;
            config.allowUnfreePredicate = pkg-settings.allowed-unfree-packages;
            config.permittedInsecurePackages = pkg-settings.allowed-insecure-packages;
            overlays = [
              nur.overlays.default
              (final: prev: {
                stable = import nixpkgs-stable {
                  inherit system;
                  config.allowUnfreePredicate = pkg-settings.allowed-unfree-packages;
                  config.permittedInsecurePackages = pkg-settings.allowed-insecure-packages;
                  overlays = [ nur.overlays.default ];
                };
              })
              (final: prev: {
                old = import nixpkgs-old {
                  inherit system;
                  config.allowUnfreePredicate = pkg-settings.allowed-unfree-packages;
                  config.permittedInsecurePackages = pkg-settings.allowed-insecure-packages;
                  overlays = [ nur.overlays.default ];
                };
              })
            ];
          };
        in
        {
          default = pkgs.mkShellNoCC {
            hardeningDisable = [ "fortify" ];
            packages = with pkgs; [
              xmake
              git
              boost
              spdlog
              cli11
              cpptrace
              gtest
              gbenchmark
              qt6.full
              gcc15
              pkg-config
              zlib
              cmake
              python313
            ];
            shellHook = ''
              export MY_NIX_PROMPT=qt_proj
            '';
          };
        });

    in
    {
      devShells = eachSystem;
    };
}
