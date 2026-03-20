#!/bin/bash
# Setup/remove macOS launchd service for ES2 pipeline
# Usage:
#   bash automation/setup_launchd.sh install [interval_minutes]
#   bash automation/setup_launchd.sh uninstall
#   bash automation/setup_launchd.sh status

LABEL="com.es2mud.pipeline"
PLIST="$HOME/Library/LaunchAgents/${LABEL}.plist"
WORKDIR="$(cd "$(dirname "$0")/.." && pwd)"
INTERVAL=${2:-30}

case "$1" in
install)
    cat > "$PLIST" << PLISTEOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN"
  "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>Label</key>
    <string>${LABEL}</string>
    <key>WorkingDirectory</key>
    <string>${WORKDIR}</string>
    <key>ProgramArguments</key>
    <array>
        <string>/bin/bash</string>
        <string>${WORKDIR}/automation/run_pipeline.sh</string>
    </array>
    <key>StartInterval</key>
    <integer>$((INTERVAL * 60))</integer>
    <key>StandardOutPath</key>
    <string>${WORKDIR}/docs/launchd_stdout.log</string>
    <key>StandardErrorPath</key>
    <string>${WORKDIR}/docs/launchd_stderr.log</string>
    <key>EnvironmentVariables</key>
    <dict>
        <key>PATH</key>
        <string>/usr/local/bin:/usr/bin:/bin:/opt/homebrew/bin</string>
        <key>HOME</key>
        <string>${HOME}</string>
    </dict>
</dict>
</plist>
PLISTEOF

    launchctl load "$PLIST"
    echo "Installed and started: every ${INTERVAL} minutes"
    echo "Plist: $PLIST"
    echo "Logs:  ${WORKDIR}/docs/launchd_stdout.log"
    echo ""
    echo "To stop:   bash automation/setup_launchd.sh uninstall"
    echo "To check:  bash automation/setup_launchd.sh status"
    ;;

uninstall)
    if [ -f "$PLIST" ]; then
        launchctl unload "$PLIST" 2>/dev/null
        rm "$PLIST"
        echo "Uninstalled: $LABEL"
    else
        echo "Not installed."
    fi
    ;;

status)
    if launchctl list | grep -q "$LABEL"; then
        echo "Running:"
        launchctl list | grep "$LABEL"
    else
        echo "Not running."
    fi
    ;;

*)
    echo "Usage: $0 {install [interval_min]|uninstall|status}"
    echo "  install 30   - run pipeline every 30 minutes"
    echo "  uninstall     - stop and remove"
    echo "  status        - check if running"
    ;;
esac
