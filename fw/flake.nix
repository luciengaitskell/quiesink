{
  description = "ESP-IDF development environment for quiesink";

  inputs.esp-dev.url = "github:mirrexagon/nixpkgs-esp-dev";

  outputs =
    { esp-dev, ... }:
    let
      darwinSystems = [
        "aarch64-darwin"
        "x86_64-darwin"
      ];
      forAllSystems =
        f:
        builtins.listToAttrs (
          map (system: {
            name = system;
            value = f system;
          }) darwinSystems
        );
    in
    {
      devShells = forAllSystems (system: {
        default = esp-dev.devShells.${system}.esp32s3-idf.overrideAttrs (oldAttrs: {
          shellHook = (oldAttrs.shellHook or "") + ''
            export ESP_IDF_VERSION=5.5

            # Work around a malformed value in nixpkgs-esp-dev.
            if [[ "$OPENOCD_SCRIPTS" == *export ]]; then
              export OPENOCD_SCRIPTS="''${OPENOCD_SCRIPTS%export}"
            fi
          '';
        });
      });
    };
}
