# import cv2
# import numpy as np
# import math
#
# # Load the image
# image = cv2.imread('blurTest.png')
#
# # Convert the image to grayscale
# gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
#
# angle_degrees = 345
# angle_radians = math.radians(angle_degrees)
#
# # Calculate size of the kernel based on angle
# kernel_size = int(2 * math.ceil(2 * abs(math.tan(angle_radians / 2))))
#
# # Tilted motion blur kernel
# kernel = np.zeros((kernel_size, kernel_size))
# kernel[int((kernel_size - 1) / 2), :] = np.ones(kernel_size) / kernel_size
#
# # Rotate the kernel by the specified angle
# rotation_matrix = cv2.getRotationMatrix2D((kernel_size / 2, kernel_size / 2), angle_degrees, 1)
# kernel = cv2.warpAffine(kernel, rotation_matrix, (kernel_size, kernel_size))
#
# # Normalize the kernel
# kernel /= np.sum(kernel)
#
# # Apply the blur kernel to the image
# blurred_image = cv2.filter2D(gray_image, -1, kernel)
#
# # Display the original and blurred images
# cv2.imshow('Original Image', gray_image)
# cv2.imshow('Blurred Image', blurred_image)
# cv2.waitKey(0)
# cv2.destroyAllWindows()



import numpy as np
import cv2

def blur_edge(img, d=31):
    h, w  = img.shape[:2]
    img_pad = cv2.copyMakeBorder(img, d, d, d, d, cv2.BORDER_WRAP)
    img_blur = cv2.GaussianBlur(img_pad, (2*d+1, 2*d+1), -1)[d:-d,d:-d]
    y, x = np.indices((h, w))
    dist = np.dstack([x, w-x-1, y, h-y-1]).min(-1)
    w = np.minimum(np.float32(dist)/d, 1.0)
    return img*w + img_blur*(1-w)

def motion_kernel(angle, d, sz=65):
    kern = np.ones((1, d), np.float32)
    c, s = np.cos(angle), np.sin(angle)
    A = np.float32([[c, -s, 0], [s, c, 0]])
    sz2 = sz // 2
    A[:,2] = (sz2, sz2) - np.dot(A[:,:2], ((d-1)*0.5, 0))
    kern = cv2.warpAffine(kern, A, (sz, sz), flags=cv2.INTER_CUBIC)
    return kern

def defocus_kernel(d, sz=65):
    kern = np.zeros((sz, sz), np.uint8)
    cv2.circle(kern, (sz, sz), d, 255, -1, cv2.LINE_AA, shift=1)
    kern = np.float32(kern) / 255.0
    return kern


if __name__ == '__main__':
    print(__doc__)
    import sys, getopt
    opts, args = getopt.getopt(sys.argv[1:], '', ['circle', 'angle=', 'd=', 'snr='])
    opts = dict(opts)
    try:
        fn = args[0]
    except:
        fn = 'blurTest.png'

    win = 'deconvolution'

    img = cv2.imread(fn, 0)
    if img is None:
        print('Failed to load fn:', fn)
        sys.exit(1)

    img = np.float32(img)/255.0
    cv2.imshow('input', img)

    img = blur_edge(img)
    IMG = cv2.dft(img, flags=cv2.DFT_COMPLEX_OUTPUT)

    defocus = '--circle' in opts

    def update(_):
        ang = np.deg2rad( cv2.getTrackbarPos('angle', win) )
        d = cv2.getTrackbarPos('d', win)
        noise = 10**(-0.1*cv2.getTrackbarPos('SNR (db)', win))

        if defocus:
            psf = defocus_kernel(d)
        else:
            psf = motion_kernel(ang, d)
        cv2.imshow('psf', psf)

        psf /= psf.sum()
        psf_pad = np.zeros_like(img)
        kh, kw = psf.shape
        psf_pad[:kh, :kw] = psf
        PSF = cv2.dft(psf_pad, flags=cv2.DFT_COMPLEX_OUTPUT, nonzeroRows = kh)
        PSF2 = (PSF**2).sum(-1)
        iPSF = PSF / (PSF2 + noise)[...,np.newaxis]
        RES = cv2.mulSpectrums(IMG, iPSF, 0)
        res = cv2.idft(RES, flags=cv2.DFT_SCALE | cv2.DFT_REAL_OUTPUT )
        res = np.roll(res, -kh//2, 0)
        res = np.roll(res, -kw//2, 1)
        cv2.imshow(win, res)

    cv2.namedWindow(win)
    cv2.namedWindow('psf', 0)
    cv2.createTrackbar('angle', win, int(opts.get('--angle', 135)), 180, update)
    cv2.createTrackbar('d', win, int(opts.get('--d', 22)), 50, update)
    cv2.createTrackbar('SNR (db)', win, int(opts.get('--snr', 25)), 50, update)
    update(None)

    while True:
        ch = cv2.waitKey()
        if ch == 27:
            break
        if ch == ord(' '):
            defocus = not defocus
            update(None)