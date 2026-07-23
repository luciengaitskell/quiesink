{
  description = "ESP-IDF development environment for quiesink";

  inputs = {
    esp-dev.url = "github:mirrexagon/nixpkgs-esp-dev";
    nixpkgs.follows = "esp-dev/nixpkgs";
  };

  outputs =
    { esp-dev, nixpkgs, ... }:
    let
      systems = [
        "aarch64-darwin"
        "x86_64-darwin"
        "aarch64-linux"
        "x86_64-linux"
      ];
      forAllSystems =
        f:
        builtins.listToAttrs (
          map (system: {
            name = system;
            value = f system;
          }) systems
        );
    in
    {
      devShells = forAllSystems (
        system:
        let
          pkgs = import nixpkgs {
            inherit system;
            overlays = [ esp-dev.overlays.default ];
            config.permittedInsecurePackages = [ "python3.13-ecdsa-0.19.1" ];
          };
        in
        {
          default = pkgs.mkShell {
            buildInputs = [ pkgs.esp-idf-xtensa ];

            shellHook = ''
              export ESP_IDF_VERSION=5.5

              # Work around a malformed value in nixpkgs-esp-dev.
              if [[ "$OPENOCD_SCRIPTS" == *export ]]; then
                export OPENOCD_SCRIPTS="''${OPENOCD_SCRIPTS%export}"
              fi
            '';
          };
        }
      );
    };
}
