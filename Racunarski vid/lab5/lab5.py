import os
os.environ["OPENCV_LOG_LEVEL"] = "ERROR"

import cv2 as cv
from cv2 import aruco
import numpy as np
import glob


BOARD = (5, 7)
MARKER_SIZE = 2
SPACE_BETWEEN = 0.4
calib_imgs = "*.jpg"
video_file = "Aruco_board.mp4"

aruco_dict = aruco.getPredefinedDictionary(aruco.DICT_6X6_1000)
detector_cfg = aruco.DetectorParameters()
aruco_board = aruco.GridBoard(BOARD, MARKER_SIZE, SPACE_BETWEEN, aruco_dict)
detector = aruco.ArucoDetector(aruco_dict, detector_cfg)


def calibrate_camera(image_glob: str):
    img_paths = glob.glob(image_glob)
    corners_all = []
    ids_all = []
    img_resolution = None

    print(f"Kalibracija sa: {len(img_paths)} slike")

    for path in img_paths:
        image = cv.imread(path)
        if image is None:
            continue
        gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
        marker_corners, marker_ids, _ = detector.detectMarkers(gray)

        if marker_ids is not None and len(marker_ids) > 0:
            corners_all.append(marker_corners)
            ids_all.append(marker_ids)
            if img_resolution is None:
                img_resolution = gray.shape[::-1]

    if not corners_all:
        raise ValueError("Neuspesna detekcija markera")

    obj_points = []
    img_points = []

    for i in range(len(corners_all)):
        objp, imgp = aruco_board.matchImagePoints(corners_all[i], ids_all[i])
        if len(objp) > 0:
            obj_points.append(objp)
            img_points.append(imgp)

    ret, camera_matrix, distortion, rvecs, tvecs = cv.calibrateCamera(
        obj_points, img_points, img_resolution, None, None
    )


    optimal_matrix, roi = cv.getOptimalNewCameraMatrix(
        camera_matrix, distortion, img_resolution, 1, img_resolution
    )

    return camera_matrix, distortion, optimal_matrix, roi


def track_pose(video_cap, camera_matrix, distortion, optimal_matrix, roi):
    print("Pracenje krece, q za izlazak")

    while True:
        ret, frame = video_cap.read()
        if not ret:
            break
        gray_frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        corners, ids, _ = detector.detectMarkers(gray_frame)

        display_frame = frame.copy()

        if ids is not None and len(ids) > 0:
            aruco.drawDetectedMarkers(display_frame, corners, ids)
            obj_p, img_p = aruco_board.matchImagePoints(corners, ids)

            if len(obj_p) > 0:
                ok, rvec, tvec = cv.solvePnP(obj_p, img_p, camera_matrix, distortion)

                if ok:
                    flip_rotation = np.array([[1, 0, 0],
                                              [0, -1, 0],
                                              [0, 0, -1]], dtype=np.float32)

                    rot_90_z = np.array([[0, 1, 0],
                                         [-1, 0, 0],
                                         [0, 0, 1]], dtype=np.float32)

                    rmat, _ = cv.Rodrigues(rvec)
                    new_rmat = rmat @ flip_rotation @rot_90_z
                    rvec_flipped, _ = cv.Rodrigues(new_rmat)

                    cv.drawFrameAxes(display_frame, camera_matrix, distortion, rvec_flipped, tvec, 5)

        corrected = cv.undistort(display_frame, camera_matrix, distortion, None, optimal_matrix)
        resized = cv.resize(corrected, None, fx=0.6, fy=0.6, interpolation=cv.INTER_AREA)
        cv.imshow("AA", resized)

        if cv.waitKey(1) & 0xFF == ord("q"):
            break


if __name__ == "__main__":
    try:
        cam_matrix, distortion_coeffs, new_matrix, region = calibrate_camera(calib_imgs)

        video_stream = cv.VideoCapture(video_file)
        if not video_stream.isOpened():
            print("Neuspesno otvaranje videa")
        else:
            track_pose(video_stream, cam_matrix, distortion_coeffs, new_matrix, region)
            video_stream.release()

    except Exception as e:
        print(f"Greka: {e}")

    cv.destroyAllWindows()