
(cl:in-package :asdf)

(defsystem "arduino_bot_controller-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "AnglesConverter" :depends-on ("_package_AnglesConverter"))
    (:file "_package_AnglesConverter" :depends-on ("_package"))
  ))