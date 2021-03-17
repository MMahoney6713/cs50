
height = 0
# Get input from the user
while True:
    height = input('Height: ')
    if height in str(range(1,10)):
        height = int(height)
        break


max_height = height


def build_row(height, max_height):

    if height == 0:
        return

    build_row(height - 1, max_height)

    print(' ' * (max_height - height) + '#' * height + '  ' + '#' * height)


build_row(max_height, max_height)