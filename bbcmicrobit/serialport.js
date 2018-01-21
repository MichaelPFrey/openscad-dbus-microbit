//https://makecode.microbit.org/#

input.calibrateCompass()
basic.showIcon(IconNames.Yes)
basic.forever(() => {
    serial.writeValue("x", input.acceleration(Dimension.X))
    serial.writeValue("y", input.acceleration(Dimension.Y))
    serial.writeValue("z", input.acceleration(Dimension.Z))
    serial.writeValue("phi", input.compassHeading())
    if (input.buttonIsPressed(Button.A)) {
        serial.writeString("A:true\r\n")
    } else {
        serial.writeString("A:false\r\n")
    }
    if (input.buttonIsPressed(Button.B)) {
        serial.writeString("B:true\r\n")
    } else {
        serial.writeString("B:false\r\n")
    }
    basic.pause(50)
})
